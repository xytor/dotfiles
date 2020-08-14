"
"                         _
"   _ __   ___  _____   _(_)_ __ ___
"  | '_ \ / _ \/ _ \ \ / / | '_ ` _ \
"  | | | |  __/ (_) \ V /| | | | | | |
"  |_| |_|\___|\___/ \_/ |_|_| |_| |_|
"
call plug#begin()
Plug 'SirVer/ultisnips'
Plug 'honza/vim-snippets'
Plug 'danielsiepmann/neotags'
Plug 'szw/vim-tags'
Plug 'itchyny/lightline.vim'
" Plug 'vim-scripts/c.vim'
Plug 'vim-scripts/sh.vim'
Plug 'norcalli/nvim-colorizer.lua'
Plug 'tpope/vim-commentary'
Plug 'dylanaraps/fff.vim'
call plug#end()

set termguicolors
lua require'plug-colorizer'

""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:lightline = {
      \ 'colorscheme': 'PaperColor',
      \ 'active': {
      \   'left': [ [ 'mode', 'paste' ],
      \             [ 'gitbranch', 'readonly', 'filename', 'modified' ] ]
      \ },
      \ 'component_function': {
      \   'filename': 'LightlineFilename',
      \ },
      \ }
function! LightlineFilename()
  return &filetype ==# 'vimfiler' ? vimfiler#get_status_string() :
        \ &filetype ==# 'unite' ? unite#get_status_string() :
        \ &filetype ==# 'vimshell' ? vimshell#get_status_string() :
        \ expand('%:t') !=# '' ? expand('%:t') : '[No Name]'
endfunction

let g:unite_force_overwrite_statusline = 0
let g:vimfiler_force_overwrite_statusline = 0
let g:vimshell_force_overwrite_statusline = 0
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
let  g:C_UseTool_cmake    = 'yes'
let  g:C_UseTool_doxygen = 'yes'
""""""""""""""""""""""""""""""""""""""""""""""""""""""
let g:sh_indent_case_labels=1
"""""""""""""""""""""""""""""""""""""""""""""""""
