/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "mohawk/riven_stacks/pspit.h"

#include "mohawk/riven.h"
#include "mohawk/riven_sound.h"

namespace Mohawk {
namespace RivenStacks {

PSpit::PSpit(MohawkEngine_Riven *vm) :
		DomeSpit(vm, kStackPspit) {

	REGISTER_COMMAND(PSpit, xpisland990_elevcombo);
	REGISTER_COMMAND(PSpit, xpscpbtn);
	REGISTER_COMMAND(PSpit, xpisland290_domecheck);
	REGISTER_COMMAND(PSpit, xpisland25_opencard);
	REGISTER_COMMAND(PSpit, xpisland25_resetsliders);
	REGISTER_COMMAND(PSpit, xpisland25_slidermd);
	REGISTER_COMMAND(PSpit, xpisland25_slidermw);
}

void PSpit::xpisland990_elevcombo(uint16 argc, uint16 *argv) {
	// Play button sound based on argv[0]
	_vm->_sound->playSound(argv[0] + 5);

	// It is impossible to get here if Gehn is not trapped. However,
	// the original also disallows brute forcing the ending if you have
	// not yet trapped Gehn.
	if (_vm->_vars["agehn"] != 4)
		return;

	uint32 &correctDigits = _vm->_vars["pelevcombo"];

	// pelevcombo keeps count of how many buttons we have pressed in the correct order.
	// When pelevcombo is 5, clicking the handle will show the video freeing Catherine.
	if (correctDigits < 5 && argv[0] == getComboDigit(_vm->_vars["pcorrectorder"], correctDigits))
		correctDigits++;
	else
		correctDigits = 0;
}

void PSpit::xpscpbtn(uint16 argc, uint16 *argv) {
	runDomeButtonMovie();
}

void PSpit::xpisland290_domecheck(uint16 argc, uint16 *argv) {
	runDomeCheck();
}

void PSpit::xpisland25_opencard(uint16 argc, uint16 *argv) {
	checkDomeSliders();
}

void PSpit::xpisland25_resetsliders(uint16 argc, uint16 *argv) {
	resetDomeSliders(10, 14);
}

void PSpit::xpisland25_slidermd(uint16 argc, uint16 *argv) {
	dragDomeSlider(10, 14);
}

void PSpit::xpisland25_slidermw(uint16 argc, uint16 *argv) {
	checkSliderCursorChange(14);
}

} // End of namespace RivenStacks
} // End of namespace Mohawk