## Super Metroid Physics Notes

This is my repository for noting oddities in the SM physics engine, from a seasoned competitive SSBM player's perspective. Morbula aims to have a cross between Super Metroid and SSBM physics, but I only have notable experience and familiarity with SSBM mechanics.

* cannot diagonally aim while ascending, i.e. holding the jump button in the air. ledge grabbing consists of ascending -> releasing jump button -> pressing aim button on the next frame.

* pressing and holding jump until after the player becomes grounded again causes the player to be put in a grounded state where they jump on the first frame that they start their grounded turnaround animation. This means that SM automatically puts the player in jump on the first frame of turnaround WITHOUT checking if jump was pressed on the previous frame when in the turning animation.


