#pragma once

namespace partyboard::ui::portraits {

// Character face icons for the menus, read from the player's own disc image (data/board.bin,
// the board status-box faces). After a successful load, RML can show character N (0-7) with
// <img src="portrait://N"/>. Safe to call repeatedly; it retries if the disc image changed.
// Returns false if there is no usable disc image (the UI then shows names only).
bool ensure_loaded();

} // namespace partyboard::ui::portraits
