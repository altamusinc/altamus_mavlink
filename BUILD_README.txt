To build python wheel, first clone the altamus pymavlink into the "pymavlink" folder

git submodule update --init --recursve

then, symbolically link the message definitions from the mavlink folder to the pymavlink folder

cd pymavlink
ln -s ../message_definitions

source a venv from the requirements, then build the wheel. May need to pip intstall 'build'

python -m build .

will build a .whl and a .tar.gz to pymavlink/dist

you can pip install this wheel