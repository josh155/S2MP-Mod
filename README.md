# S2MP-Mod | Call of Duty: WWII Client Modification

Discord Server: [https://discord.gg/Wbb5YMZrHG](https://discord.gg/Wbb5YMZrHG)

S2MP-Mod is a quality-of-life and debugging focused client modification for Call of Duty: WWII. It restores stripped commands and dvars, adds new tools for testing and exploration, and makes working with configs and custom binds much easier.

## Highlights
- Internal and external developer consoles
- Restored access to many stripped or hidden commands and dvars
- Dvar name mapping, so friendly names can be used instead of engine numeric ids
- Optional dvar prefixes like `set`, `seta`, `toggle`, `togglep`, and `reset`
- Bare dvar input support such as `cg_fovscale 1.3`
- Custom bind system with saved binds stored in `players2/s2mp_custom_binds.dat`
- `exec` support for cfg files in `players2`
- Automatic `autoexec.cfg` creation on startup
- Support for encrypted `system_config_mp.cfg`
- Protection against cfg files infinitely executing themselves
- Custom image loading support
- Asset dumping and debugging helpers for LUI, scripts, stringtables, rawfiles, images, and more
- Multiplayer and Zombies utility commands, including unlock helpers

## Common Commands
Examples of commands available in the client:

- Movement and gameplay: `noclip`, `ufo`, `god`, `trans`
- Map and session tools: `map`, `map_restart`, `fast_restart`
- Rendering and view tools: `r_fullbright`, `r_wireframe`, `r_togglePortals`
- Debugging: `luidbg`, `entdbg`, `acdbg`, `intcondbg`, `listcmd`
- Inventory and weapons: `give`, `dropweapon`, `unlockall`
- Bind management: `bind`, `unbind`, `unbindall`
- Config execution: `exec <file>`

## Configs And Binds
- Put cfg files in your `players2` folder
- `autoexec.cfg` is created automatically if it does not already exist
- `exec` can run normal cfg files line by line
- `system_config_mp.cfg` is supported and will be decrypted automatically before execution
- Custom binds are loaded at startup and saved back to `players2/s2mp_custom_binds.dat`

## Notes
- Extract the contents into the root folder of your WWII Steam installation
- Run the launcher and choose Multiplayer or Zombies

## Build
- Clone the repository
- Run `generate.bat` to fetch dependencies
- Open `s2mp-mod.sln` in Visual Studio 2022 and build

## Disclaimer
This project is for educational and personal use only. I am not responsible for bans, penalties, or any other consequences that may result from using this client. Use it at your own risk.
