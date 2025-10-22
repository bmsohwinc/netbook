import asyncio
import logging
from typing import Optional

from aioquic.asyncio import QuicConnectionProtocol, connect
from aioquic.quic.configuration import QuicConfiguration
from aioquic.quic.events import QuicEvent, StreamDataReceived

# Configure logging
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - CLIENT - %(levelname)s - %(message)s"
)

class SimpleClientProtocol(QuicConnectionProtocol):
    """
    This protocol handles events for the client connection.
    It primarily waits for a response from the server.
    """
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self._response_received = asyncio.Event()

    def quic_event_received(self, event: QuicEvent) -> None:
        if isinstance(event, StreamDataReceived):
            # Data has been received from the server
            response_data = event.data.decode()
            print(f"Server says: {response_data}")
            self._response_received.set()

    async def wait_for_response(self):
        """Wait until the response received event is set."""
        await self._response_received.wait()

    def reset(self):
        """Resets the event to allow waiting for the next message."""
        self._response_received.clear()


remote_addr = ("localhost", 4433)
async def main() -> None:
    """
    Main function to set up and run the QUIC client.
    """
    host = "localhost"
    port = 4433
    aio_loop = asyncio.get_running_loop()
    
    logging.info(f"Connecting to QUIC server at {host}:{port}")

    # Create a QUIC configuration
    configuration = QuicConfiguration(
        is_client=True,
        alpn_protocols=["h3"] # Must match the server's ALPN
    )

    # Load the server's self-signed certificate to verify it
    try:
        configuration.load_verify_locations("cert.pem")
        logging.info("Server certificate loaded for verification.")
    except FileNotFoundError:
        logging.error("Error: 'cert.pem' or 'key.pem' not found.")
        logging.error("Please generate it using the openssl command in README.md")
        return

    # Connect to the server
    async with connect(
        host,
        port,
        configuration=configuration,
        create_protocol=SimpleClientProtocol,
    ) as client:
        print("\nConnected! Type a message and press Enter.")
        print("Type 'x' to exit.\n")

        user_msgs = ["hi", "m", "hello", "x"]
        
        for user_message in user_msgs:
            if user_message == 'm':
                try:
                    # Migrate
                    logging.info("Starting migration")
                    client._transport.close()
                    logging.info("Closed transport")
                    new_transport, _ = await aio_loop.create_datagram_endpoint(lambda: client, local_addr=("::", 0))#, remote_addr=remote_addr)
                    logging.info("Created datagram")
                    # client._transport = new_transport
                    logging.info("Completed migration?")
                except Exception as e:
                    logging.info(f"Migration failed: {e}")
                continue

            if user_message == 'x':
                print("\nOK, exiting chat.")
                break

            # 1. Get a NEW stream ID for each message
            stream_id = client._quic.get_next_available_stream_id()
            logging.info(f"Got the next id: {stream_id}")
            
            # 2. Send the message, ending the stream for this transaction
            quic_payload = user_message.encode()

            try:
                logging.info("Sending data now...")
                client._quic.send_stream_data(stream_id, quic_payload, end_stream=True)
                # 3. Wait for the server's echo response
                await client.wait_for_response()
            except Exception as e:
                print(e)
        
            # 4. CRITICAL: Reset the event for the next message
            client.reset()

            await asyncio.sleep(2)
        
        logging.info("Chat finished. Closing connection.")
        client.close()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except Exception as e:
        logging.error(f"An error occurred: {e}")

