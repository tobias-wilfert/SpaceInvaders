mkdir build
cd build
cmake ..
make
chmod a+x SpaceInvaders
./SpaceInvaders ../resources/levels/mexicanStandoff.xml ../resources/levels/classic.xml ../resources/levels/battleOfThermopylae.xml
