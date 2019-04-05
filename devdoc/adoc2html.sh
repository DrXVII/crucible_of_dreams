#!/bin/bash

asciidoctor -a stylesheet=$PWD/adoc_styles/book.css $1
