" This should be located at $(HOME)/AppData/Local/nvim/
set runtimepath^=~/.vim runtimepath+=~/.vim/after
let &packpath = &runtimepath
source ~/.vimrc
