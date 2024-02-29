"-----------------------------------------------------
" Vundle Configuration
set nocompatible
filetype off

set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()

" Vundle manager
Plugin 'VundleVim/Vundle.vim'

" Colorschemes
Plugin 'kristijanhusak/vim-hybrid-material'
Plugin 'cocopon/iceberg.vim'
Plugin 'arcticicestudio/nord-vim'
Plugin 'sjl/badwolf'
Plugin 'lifepillar/vim-solarized8'
Plugin 'scheakur/vim-scheakur'
Plugin 'Badacadabra/vim-archery'

" PolyglGlot - Multi language syntax highlight
Plugin 'sheerun/vim-polyglot'

" Auto Pairs for comma, parethesis, etc
Plugin 'jiangmiao/auto-pairs'

" Nerd Tree - file explorer
Plugin 'preservim/nerdtree'

" Tag List - functions and classes list
Plugin 'vim-scripts/taglist.vim'

" File Switch - switch from cpp hpp files
Plugin 'derekwyatt/vim-fswitch'

" You Complete Me
Plugin 'ycm-core/YouCompleteMe'

" Incsearch - Beautiful in file search
Plugin 'haya14busa/incsearch.vim'

" Ctrl-Space - Vim buffer files
Plugin 'vim-ctrlspace/vim-ctrlspace'

call vundle#end()

"-----------------------------------------------------
" Plugin Config

" Auto Pairs
let g:AutoPairsShortcutToggle = '<C-P>'

" NERDTree
let NERDTreeShowBookmarks = 1
let NERDTreeShowHidden = 1
let NERDTreeShowLineNumbers = 0
let NERDTreeMinimalMenu = 1
let NERDTreeWinPos = "left"
let NERDTreeWinSize = 31

" Tag List
let Tlist_GainFocus_On_ToggleOpen = 1
let Tlist_WinWidth = 70
let Tlist_Auto_Highlight_Tag = 0
let Tlist_File_Fold_Auto_Close = 1
let Tlist_Use_Right_Window = 1
let Tlist_Display_Prototype = 1
let Tlist_Display_Tag_Scope = 1
let Tlist_Close_On_Select = 1

" fswitch
au! BufEnter *.cpp let b:fswitchdst = 'hpp,h,hh'
au! BufEnter *.h let b:fswitchdst = 'cpp,c,cc'

" incsearch
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

" CtrlSpace
if has("gui_running")
    let g:CtrlSpaceSymbols = { "File": "◯", "CTab": "▣", "Tabs": "▢"  }
endif
hi link CtrlSpaceNormal   PMenu
hi link CtrlSpaceSelected PMenuSel
hi link CtrlSpaceSearch   Search
hi link CtrlSpaceStatus   StatusLine

"-----------------------------------------------------
" Vim Configuration
syntax enable
syntax on

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

filetype indent plugin on

colorscheme scheakur

"-----------------------------------------------------
" Key mappings

" You Complete Me
nnoremap <F1> :YcmCompleter GetType<CR>
nnoremap <F2> :YcmCompleter GoToDeclaration<CR>
nnoremap <F3> :YcmCompleter GoToDefinition<CR>

" fswitch
nmap <F4> :vsplit <bar> :wincmd l <bar> :FSRight<CR>

" Pre-commit hook
nnoremap <F5> :!sh -xc 'pre-commit run --all'<CR>

" NERDTree
nnoremap <F7> :NERDTreeToggle<CR>

" Tag List
nnoremap <silent> <F8> :TlistToggle<CR>

" CtrlSpace
imap <C-p> <C-Space>

" Help message
nnoremap <F9> :echo "Help Commands:\n\t
    \ <F1> Go type\n\t
    \ <F2> Go to declaration\n\t
    \ <F3> Go to definition\n\t
    \ <F4> Header/Source switch\n\t
    \ <F5> Pre-commit hook\n\t
    \ <F6> -------------\n\t
    \ <F7> Nerd Tree\n\t
    \ <F8> Tag List\n\t
    \ <F9> This help message"<CR>
