Mock HL2SDK
-----------

This is a highly experimental and very incomplete "mock" of the HL2SDK. It's
intended for testing of Metamod:Source, SourceMod, and another server plugins.
You don't need to download Steam or srcds. There is no Valve code in the
implementation.

Most functionality is stubbed, but console commands and cvars work.

# Usage

You will need AMBuild. Make sure you've updated. It relies on AMBuild changes
made on 9-22-2021.

You will need to build both hl2sdk-mock and Metamod:Source:

    cd metamod-source
    python3 configure.py --sdks=mock --targets=x86_64
    ambuild objdir

    cd -
    cd hl2sdk-mock
    python3 configure.py --targets=x86_64
    ambuild objdir

Once you have it built, you will need to make a gamedir. Because many plugins
use real filesystem paths, we cannot expose a virtual filesystem. For ease of
development you can use `build_gamedir.sh`. It creates a filesystem structure
given a template directory, and then creates symlinks for all files. This eases
development as you don't have to rsync or copy new files when you rebuild a
plugin.

For example:

    mkdir ~/gamedir
    bash build_gamedir.sh ~/gamedir ../metamod-source/objdir/package
    bash build_gamedir.sh ~/gamedir ../sourcemod/objdir/package

Now you can launch mock srcds:

    ./objdir/dist/x86_64/srcds -game_dir ~/gamedir +map de_thunder

By default the console is in interactive mode. While in interactive mode the
server is paused and commands may be entered. Typing a command will cause it to
be immediately processed. You can find available commands with "cvarlist".

To put the server into "run" mode, you can use "run" or "continue". This will
process "frames" until you enter Ctrl+C to re-enter interactive mode.

We don't have a fully asynchronous interactive console like true srcds. It's
quite tricky to do without lots of OS-specific console hacks.

# Working Commands

The following commands are implemented, in that they do something:

 - changelevel (any string is accepted as a map name)
 - continue (run frames, mock srcds specific)
 - cvarlist
 - exit
 - plugin\_load
 - quit
 - run (run frames, mock srcds specific)
 - think (run one frame, mock srcds specific)

Commands/cvars added by Metamod, SourceMod, and other plugins will all be
present as well.

# Development

Contributions are very welcome.

After changing tier1, tier0, vstdlib, or mathlib mock sources, you will need to
run update\_prebuilds.sh, and then rebuild any C++ plugins. For security
reasons, we cannot accept third-party commits with prebuilts, but we can
generate new ones as part of a pull request.

As of this writing we do not use any Valve code to implement any function
definition. The minimalist approach here was to reduce the amount of things we
had to get working. If needed we can re-evaluate this: eg, maybe it makes sense
to import something like mathlib from the public SDK.
