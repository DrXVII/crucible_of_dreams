(TeX-add-style-hook
 "design_doc"
 (lambda ()
   (TeX-add-to-alist 'LaTeX-provided-class-options
                     '(("book" "a4paper" "10pt")))
   (TeX-add-to-alist 'LaTeX-provided-package-options
                     '(("inputenc" "utf8")))
   (TeX-run-style-hooks
    "latex2e"
    "book"
    "bk10"
    "inputenc")
   (TeX-add-symbols
    "Projectname"
    "Enginename"
    "Gamename"))
 :latex)

