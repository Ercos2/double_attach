rm -r src/*
rm -r build/*
mkdir src
mkdir build
asn1c rrc.asn1 -D src -pdu=RRCConnectionSetup -no-gen-OER -fcompound-names -no-gen-example -fno-include-deps
gcc -g -Isrc -I. -o build/attach main.c Attach_coder.c src/*.c -lsctp -DPDU=S1SetupRequest -DASN_DISABLE_OER_SUPPORT
./build/attach