import asyncio
import logging
from typing import Optional

from aioquic.asyncio import QuicConnectionProtocol, serve
from aioquic.quic.configuration import QuicConfiguration
from aioquic.quic.events import QuicEvent, StreamDataReceived

# Configure logging to see aioquic's output
logging.basicConfig(
    level=logging.INFO,
    format="%(asctime)s - SERVER - %(levelname)s - %(message)s"
)

# Define the server protocol
class SimpleServerProtocol(QuicConnectionProtocol):
    """
    This protocol handles incoming QUIC events.
    When it receives data on a stream, it simply echoes it back.
    """
    def quic_event_received(self, event: QuicEvent) -> None:
        logging.info(f">>> Something came: {event}")

        if isinstance(event, StreamDataReceived):
            # Data has been received from the client
            request_data = event.data
            logging.info(f"Received from client: '{request_data.decode()}' on stream {event.stream_id}")

            # Echo the data back to the client on the same stream
            logging.info(f"Echoing back to client on stream {event.stream_id}")
            self._quic.send_stream_data(event.stream_id, request_data, end_stream=True)


async def main() -> None:
    """
    Main function to set up and run the QUIC server.
    """
    host = "localhost"
    port = 4433
    
    logging.info(f"Starting QUIC echo server on {host}:{port}")

    # Create a QUIC configuration
    configuration = QuicConfiguration(
        is_client=False,
        alpn_protocols=["h3"] # Application-Level Protocol Negotiation
    )

    # Load the self-signed certificate and private key
    try:
        configuration.load_cert_chain("cert.pem", "key.pem")
        logging.info("Certificate and key loaded successfully.")
    except FileNotFoundError:
        logging.error("Error: 'cert.pem' or 'key.pem' not found.")
        logging.error("Please generate them using the openssl command in README.md")
        return

    # Start the server using aioquic's `serve` utility
    server = await serve(
        host=host,
        port=port,
        configuration=configuration,
        create_protocol=SimpleServerProtocol,
    )

    logging.info("Server is listening. Press Ctrl+C to stop.")
    
    # Keep the server running indefinitely
    try:
        await asyncio.Future()
    except asyncio.CancelledError:
        logging.info("Server is shutting down.")
    finally:
        server.close()


if __name__ == "__main__":
    try:
        asyncio.run(main())
    except KeyboardInterrupt:
        pass

