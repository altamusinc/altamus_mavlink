TITAN_MDEF_PATH="./message_definitions/v1.0/titan.xml"
source ./.venv/bin/activate
python -m pymavlink.tools.mavgen --lang=C --wire-protocol=2.0 --output=src/mavlink/v2.0 $TITAN_MDEF_PATH
python -m pymavlink.tools.mavgen --lang=WLua --wire-protocol=2.0 --output=src/mavlink/titan_mavlink $TITAN_MDEF_PATH