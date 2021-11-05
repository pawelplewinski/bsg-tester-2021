/**
 * @file boot_support.h
 * @brief DESY HPM.1 Bootloader support
 *
 * @copyright (C) 2015 Deutsches Elektronen-Synchrotron, Hamburg, Germany (DESY)
 * @copyright (C) 2015 Lodz University of Technology, Lodz, Poland  (TUL) 
 * @copyright (C) 2014 National Center of Nuclear Research, Otwock-Swierk, Poland (NCBJ)
 * @author Jaroslaw Szewinski (NCBJ)
 * @author Piotr Perek (TUL)
 * @author Aleksander Mielczarek (TUL) 
 * @author Aleksander Szubert (TUL)
 * @author Dariusz Makowski (TUL)
 * @author Vahan Petrosyan (DESY)
 * @par License
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
//-----------------------------------------------------------------------------
#ifndef BOOT_SUPPORT_H
#define BOOT_SUPPORT_H
#ifdef __cplusplus
 extern "C" {
#endif

//-----------------------------------------------------------------------------
#include <stdbool.h>
//-----------------------------------------------------------------------------
bool			boot_is_bootloader_present(void);
void			boot_start_bootloader(void);
void			boot_set_firmware_valid_flag(void);
void			boot_clear_firmware_valid_flag(void);
bool            boot_get_firmware_valid_flag(void);
bool			boot_check_bootloader_erased(void);
//-----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

#endif // MMC_BOOT_H
//-----------------------------------------------------------------------------
