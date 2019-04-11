# mim_av_pass

1)Open project with visual studio, and install missing dependancies
2)First replace common flagging words such as mimikatz, kiwi, gentilwiki, benjamin, etc

3)then split file until you reach close to a sufficient numper of bytes (arround 20 its good to spot the word that flags):
head -c 10000 mimikatz > test.exe

4)drop test.exe to VM with AV, if it spots it as virus split to half:
head -c 5000 mimikatz > test.exe

5)You will reach at sometime that in 2330 its ok but in 2350 is alerting.
6)Open test.exe with a hexeditor, go to last bytes, and find the suspicious word
7)Then go to the project and change that word