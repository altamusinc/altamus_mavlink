ALTAMUS_MDEF_PATH="./message_definitions/v1.0/altamus.xml"
source ./.venv/bin/activate
python -m pymavlink.tools.mavgen --lang=C --wire-protocol=2.0 --output=src/mavlink/v2.0 $ALTAMUS_MDEF_PATH
python -m pymavlink.tools.mavgen --lang=WLua --wire-protocol=2.0 --output=src/mavlink/altamus_mavlink $ALTAMUS_MDEF_PATH
cd altamus_mavlink_dart
dart run ./tool/generate.dart -d ../$ALTAMUS_MDEF_PATH