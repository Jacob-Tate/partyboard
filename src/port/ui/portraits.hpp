#pragma once

namespace partyboard::ui::portraits {

// Menu pictures read from the player's own disc image (nothing from the game ships with Party Board).
// Each loader is safe to call repeatedly; it retries if the disc image setting changed. It returns
// false if the pictures can't be read, and the UI then shows names only.

// Character faces (data/board.bin 0x2E-0x35, the board status-box icons): <img src="portrait://N"/>,
// N = character id 0-7.
bool ensure_loaded();

// Board pictures from the party menu (data/ment.bin 0x3C bitmaps 5-9, 0x3E bitmap 1):
// <img src="board://N"/>, N = board 0-5.
bool ensure_boards_loaded();

} // namespace partyboard::ui::portraits
