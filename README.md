# RSA-Modification

## Idea
- C/C++ cmdline-tool -> decrypts/encryps the chiffre
  -  the C++ tool had one strong (own) crypting algorithm and one for learning wich only is RSA
  -  need the type (encryption/decryption), an input-file, an output-file <, and an step-documatation-file>
    -  e.g.: `crypt -e input.txt -o output.txt -d doc.txt`
- WinForm-UI -> manage the access to the cmdline-tool
