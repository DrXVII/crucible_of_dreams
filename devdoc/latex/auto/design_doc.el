(TeX-add-style-hook
 "design_doc"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("book" "a4paper" "10pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8") ("xcolor" "table")))
   (TeX-run-style-hooks
    "latex2e"
    "book"
    "bk10"
    "inputenc"
    "mathtools"
    "minted"
    "hyperref"
    "tabu"
    "xcolor")
   (TeX-add-symbols
    '("TODO" 1)
    "Projectname"
    "Enginename"
    "Gamename"))
 :latex)

