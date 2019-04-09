(TeX-add-style-hook
 "design_doc"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("book" "a4paper" "10pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("fontenc" "T1") ("inputenc" "utf8") ("xcolor" "table")))
   (add-to-list 'LaTeX-verbatim-environments-local "minted")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "path")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "url")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "nolinkurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperbaseurl")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperimage")
   (add-to-list 'LaTeX-verbatim-macros-with-braces-local "hyperref")
   (add-to-list 'LaTeX-verbatim-macros-with-delims-local "path")
   (TeX-run-style-hooks
    "latex2e"
    "book"
    "bk10"
    "fontenc"
    "inputenc"
    "mathtools"
    "minted"
    "hyperref"
    "xcolor")
   (TeX-add-symbols
    '("admonition" ["argument"] 2)
    '("codew" 1)
    '("textbi" 1)
    '("think" 1)
    '("note" 1)
    '("danger" 1)
    '("TODO" 1)
    "Projectname"
    "Enginename"
    "Gamename"
    "enginenamespace")
   (LaTeX-add-xcolor-definecolors
    "red"
    "globaltablecolor"
    "blue"
    "orange"))
 :latex)

