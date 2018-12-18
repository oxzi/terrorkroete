# Terrorkröte

<p align="center">
  <img width="500" height="375" src="https://i.imgur.com/KZuHILo.jpg">
</p>


## About Terrorkröte

The *Terrorkröte* is a fun project based on an abandoned toy. This very special
turtle contains one movable and five transparent plates on its armature. A
switch was glued behind the movable one and each transparent plate was equipped
with a LED. The parts were soldered to an ESP32 devboard. Two LEDs for the
turtle's eyes and a speaker - connected to a PAM8403 amplifier - were also
attached to the ESP32.

After powering up the *Terrorkröte*, the speaker starts playing a song, the
transparent plates are flickering randomly and the red eyes are glowing. When
the song stops, the flickering disappears and only the eyes are still glowing.
Pressing the top plate resets our turtle.

A demonstration is available [online][twitter-kroete].


## Creating the Song or *"It does not compile!!!11"*

The song is not available in this repository, because reasons. However, creating
a C-file of your MP3-file is very easy.

```bash
# Crop MP3 sample
ffmpeg -ss $START_SEC -t $DURATION_SEC -i $INPUT_FILE -ac 1 $OUTPUT_MP3
# Create C include file
xxd -i $OUTPUT_MP3 > ./this-repo/src/$OUTPUT_H
```

Afterwards modify the `include` and its variale names for
`AudioFileSourcePROGMEM` in the `main.cpp` file.

The pins are also defined in the `leds`, `eyes` and `button` variable.
Furthermore, the ESP32's `RX` port should be connected to the amplifier's input.

You can flash your personal *Terrorkröte* with [platformio].

```bash
pio run -t upload
```


[twitter-kroete]: https://twitter.com/lnrthm/status/1074763025381498881
[platformio]: https://platformio.org/
