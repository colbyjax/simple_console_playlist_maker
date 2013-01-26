SCPM - (simple console playlist maker)
======================================

Console based application designed to build music playlists.  Specifically useful for headless linux servers.

Starting Application
=====================
scpm [option] target
* i.e. scpm (This will default to entries in 'conf' file)
* i.e. scpm -m /home/music -f /home/playlists/playlist.m3u (Overrides entries in conf file)

-m    Root of music directory
-f    File to store playlist

Using Application
=================
* General usage: Music will appear as a numbered list.  To add a file to the playlist, choose the number and
* hit enter.  If the number chosen is a directory, it will display the files in that directory.  It will only
* display 25 listings at a time, configurable by the 'conf' file.  Hit 'n' enter to scroll through the next
* page of listings.  This will cycle through to the beginning of the listings.  Hit 'h' enter, to take you to 
* your music root at any time.  Hit 'u' enter to move up one directory.  Other options listed below.

* h   - (Home) Go to Home Screen with your Starting Path at any time
* n   - (Next) This will scroll through the next page of Entries in the directory if more exist.  Will scroll through the beginning again.
* u   - (Up) Go up a directory
* d # - (Delete) Where '#' is the number in the playlist.  This will remove entry from playlist.
* List Number - (#) Where '#' is the number in the Music Directory.  This will add an entry to the playlist if a file.  If the entry is a directory, it will navigate to the directory and show its entries
* s   - (Save) Saves the Playlist.  File to save is configurable in 'conf' or command line.
* q   - (Quit) Exits the Program

