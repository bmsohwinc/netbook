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
            logging.info(f"Received from server: '{response_data}'")
            self._response_received.set()

    async def wait_for_response(self):
        """Wait until the response received event is set."""
        await self._response_received.wait()


async def main() -> None:
    """
    Main function to set up and run the QUIC client.
    """
    host = "localhost"
    port = 4433
    
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
        logging.error("Error: 'cert.pem' not found.")
        logging.error("Please generate it using the openssl command in README.md")
        return

    # Connect to the server
    async with connect(
        host,
        port,
        configuration=configuration,
        create_protocol=SimpleClientProtocol,
    ) as client:
        # `client` is an instance of SimpleClientProtocol
        
        # Get the next available stream ID to send data
        stream_id = client._quic.get_next_available_stream_id()
        message = b"Hello, Server!"
        
        logging.info(f"Sending to server: '{message.decode()}' on stream {stream_id}")
        
        # Send data to the server on the created stream
        client._quic.send_stream_data(stream_id, message, end_stream=True)
        
        # Wait for the server's response
        await client.wait_for_response()
        
        logging.info("Response received. Closing connection.")


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except Exception as e:
        logging.error(f"An error occurred: {e}")
