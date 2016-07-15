#WonderSwan MIDI2MML Converter
Convert Musical Instrument Digital Interface (MIDI/SMF) compositions to 
Wonderswan Music Macro Language (MML) files that is readable and 
editable. Tool to improve the development process of WonderSwan 
chipmusic (DAW => MIDI conversion => MIDI2MML => MML2FX => FX2WSC). 
Intended to work with the [Wonderswan Total Sound Driver (WTD)] 
(http://shaw.la.coocan.jp/wtd/) which was created by S.W. There are 
SMF2MML converters out there however a readily available one for the WS 
is much needed for easy implemention. 

##Main Goals
* Parse essential data
* Read from all 3 types of MIDI formats (0, 1, and 2)

##Personal Goals
* Learn how to parse data
* Learn the importance of pointers and how they're used
* Improve my C Coding capabilties

##Conversion Restrictions (at the project's current stage)
* 4 channels, one voice per channel
* No implementation of wave data/wave tables......yet
* Only Format 1 at the moment.
* Restricited to the following Meta Messages: Time Signature, Tempo, End of 
Track
* Restricted to the following MIDI Messages: Note Off, Note On, Pitch Change
