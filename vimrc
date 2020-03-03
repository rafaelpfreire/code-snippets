set nocompatible

set shiftwidth=4
set tabstop=4
set expandtab
set autoindent

set hidden
set showmatch
set wildmenu
set showcmd

set mouse=a
set ignorecase
set hlsearch
set nowrap
set number

set backspace=indent,eol,start

syntax enable
syntax on

hi Search cterm=NONE ctermfg=grey ctermbg=darkblue
hi ErrorMsg cterm=NONE ctermfg=grey ctermbg=darkred

" Attempt to determine the type of a file based on its name and possibly its
" contents. Use this to allow intelligent auto-indenting for each filetype,
" and for plugins that are filetype specific.
filetype indent plugin on

"------------------------------------------------------------
" Vundle Configuration
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

Plugin 'VundleVim/Vundle.vim'
Plugin 'Valloric/YouCompleteMe'
Plugin 'rdnetto/YCM-Generator'
Plugin 'scrooloose/nerdtree'
Plugin 'davidhalter/jedi-vim'
Plugin 'vim-ctrlspace/vim-ctrlspace'
Plugin 'haya14busa/incsearch.vim'
Plugin 'vim-scripts/taglist.vim'
Plugin 'jiangmiao/auto-pairs'
Plugin 'vim-syntastic/syntastic'

call vundle#end()

"------------------------------------------------------------
" Mappings Configuration

nnoremap <F1> :YcmCompleter GetType<CR>
nnoremap <F2> :YcmCompleter GoToDeclaration<CR>
"nnoremap <F3> :YcmCompleter GoToDefinition<CR>

nnoremap <F5> :!sh -xc 'clang-format -style=file -i $(find ./ -name *.cpp -o -name *.hpp -o -name *.c -o -name *.h)'<CR>
"nnoremap <F5> :!sh -xc 'find . -regex \'.*\.\(cpp\|hpp\|cu\|c\|h\)\' -exec clang-format -style=file -i {} \;'<CR>
nnoremap <F7> :NERDTreeToggle<CR>
nnoremap <silent> <F8> :TlistToggle<CR>
imap <C-p> <C-Space>

" Help message
nnoremap <F9> :echo "Help Commands:\n\t
    \ <F1> Get type\n\t
    \ <F2> Go to declaration\n\t
    \ <F3> -------------\n\t
    \ <F4> -------------\n\n\t
    \ <F5> Clang format\n\t
    \ <F6> -------------\n\t
    \ <F7> Nerd tree\n\t
    \ <F8> Clang format\n\n\t
    \ <F9> This help message"<CR>

"------------------------------------------------------------
" YouCompleteMe Plugin Configuration

set statusline+=%#warningmsg#
set statusline+=%{SyntasticStatuslineFlag()}
set statusline+=%*

let g:syntastic_always_populate_loc_list = 1
let g:syntastic_auto_loc_list = 1
let g:syntastic_check_on_open = 1
let g:syntastic_check_on_wq = 0

"------------------------------------------------------------
" YouCompleteMe Plugin Configuration

hi link YcmErrorSign ErrorMsg
"hi link YcmErrorLine ErrorMsg
hi link YcmErrorSection ErrorMsg
hi YcmWarningSign cterm=NONE ctermfg=grey ctermbg=darkblue
"hi YcmWarningLine cterm=NONE ctermfg=black ctermbg=darkblue
hi YcmWarningSection cterm=NONE ctermfg=black ctermbg=darkblue

"------------------------------------------------------------
" ToggleList Plugin Configuration

let Tlist_GainFocus_On_ToggleOpen = 1
let Tlist_WinWidth = 70
let Tlist_Auto_Highlight_Tag = 0
let Tlist_File_Fold_Auto_Close = 1
let Tlist_Use_Right_Window = 1
let Tlist_Display_Prototype = 1
let Tlist_Display_Tag_Scope = 1
let Tlist_Close_On_Select = 1

"------------------------------------------------------------
" CtrlSpace Plugin Configuration

if has("gui_running")
        " Settings for MacVim and Inconsolata font
        let g:CtrlSpaceSymbols = { "File": "◯", "CTab": "▣", "Tabs": "▢"  }
endif

hi link CtrlSpaceNormal   PMenu
hi link CtrlSpaceSelected PMenuSel
hi link CtrlSpaceSearch   Search
hi link CtrlSpaceStatus   StatusLine

"------------------------------------------------------------
" Incsearch Plugin Configuration

map /  <Plug>(incsearch-forward)
map ?  <Plug>(incsearch-backward)
map g/ <Plug>(incsearch-stay)

let g:incsearch#auto_nohlsearch = 1
map n  <Plug>(incsearch-nohl-n)
map N  <Plug>(incsearch-nohl-N)
map *  <Plug>(incsearch-nohl-*)
map #  <Plug>(incsearch-nohl-#)
map g* <Plug>(incsearch-nohl-g*)
map g# <Plug>(incsearch-nohl-g#)
