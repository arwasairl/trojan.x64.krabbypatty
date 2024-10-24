# krabbypatty

A Kristik Trojan heavily based off of trojan.x64.ILOVEYUUKA. This trojan does not utilize a restart as it does not use custom drivers for the BSOD sequence.

# Usage
The program will ONLY run when the month of the system is set to March, September, or November. It will not run on any other months.

# Payloads
- Overrides desktop wallpaper
- Plays beautiful kristik rap
- Spams I LOVE KRISTIK files
- Replaces master boot record with custom one (BIOS VM)
- Runs shutdown script
- Spams popup dialogs
- Scans and deletes task manager
- Deletes system 32
- Spams random links
- Melt screen

# Todo
- File encryption
- GUID partition table mangle
- User account hijacking
- Icon injection

# Building
To build this, open the solution with VS2022 and build. If you want to change the MBR's message, edit the the data.asm file and build with NASM.

