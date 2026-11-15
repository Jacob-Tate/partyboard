Party Board - cross-machine determinism test
=============================================

What it does
  Plays the same computer-only 3-turn game on each of the six boards, then compares every
  frame of game state against logs recorded on the original PC with this exact build.
  If every frame matches, the two PCs would stay in sync in online play.

You need
  - Windows 10/11 (64-bit) with a GPU that supports DirectX 12 or Vulkan
  - Your own copy of the disc image: Mario Party 4 (USA) (Rev 1)  (.rvz or .iso)

Run it
  1. Unzip this folder anywhere.
  2. Open a Command Prompt in the folder and run:

       determinism-test.bat "C:\path\to\Mario Party 4 (USA) (Rev 1).rvz"

  3. Leave it alone for about 20-25 minutes. A game window opens and closes six times,
     running faster than normal. Sound may be choppy - that is expected in fast mode.
     Don't drag or close the windows.

Result
  Each board prints MATCH or MISMATCH. At the end it says either
  "All boards match" or where to find the results folder.
  If anything mismatches, crashes or hangs, zip the results\<timestamp> folder and send it back.

Note
  partyboard.exe stores its settings in %APPDATA%\MarioPartyRD\Party Board\. You can delete
  that folder afterwards.
