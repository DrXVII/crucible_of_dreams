#!/bin/bash

asciidoctor -a stylesheet=$PWD/doc_stylesheets/book.css $1
