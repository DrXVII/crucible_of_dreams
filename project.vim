:e src/main.cpp
:vs

:TlistToggle

"move tag-list (TlistToggle) to the far right via rotating twice
:execute "normal! 2\<C-w>\<C-r>"

:NERDTree

"make middle screens of equal proportions
:execute "normal! \<C-w>="

"select the middle-right window as the selection is currently NERDTree (left)
:execute "normal! 2\<C-w>l"
