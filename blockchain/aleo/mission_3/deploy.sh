# PRIVATEKEY="APrivateKey1zkpBjpEgLo4arVUkQmcLdKQMiAKGaHAQVVwmF8HQby8vdYs"
PRIVATEKEY="APrivateKey1zkpB9Rp33asKDz65tLuNkhyXcZifYMAUQfX63Z2VBrGJ5tn"
APPNAME="mission_3"
DEVNET_API_URL="http:///127.0.0.1:3030"

snarkos developer deploy "${APPNAME}.aleo" \
  --private-key "${PRIVATEKEY}" \
  --query "${DEVNET_API_URL}" \
  --priority-fee 1000000 \
  --broadcast "${DEVNET_API_URL}/testnet3/transaction/broadcast" \
  --path "./build/" \
