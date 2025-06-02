After changing definitions run this:

```bash
python -m pymavlink.tools.mavgen --lang=C --wire-protocol=2.0 --output=src/mavlink/v2.0 message_definitions/v1.0/altamus.xml
python -m pymavlink.tools.mavgen --lang=WLua --wire-protocol=2.0 --output=src/mavlink/altamus_mavlink message_definitions/v1.0/altamus.xml
```