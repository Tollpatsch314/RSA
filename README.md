# RSA-Modification

## Idea
- C/C++ cmdline-tool -> decrypts/encryps the chiffre
  -  the C++ tool had one strong (own) crypting algorithm and one for learning wich only is RSA
  -  need the type (encryption/decryption), an input-file, an output-file <, and an step-documatation-file>
    -  e.g.: `crypt -e input.txt -o output.txt -d doc.txt`
- WinForm-UI -> manage the access to the cmdline-tool

## Sources
- https://www.happycoders.eu/de/algorithmen/o-notation-zeitkomplexitaet/

### Prime Numbers
- https://de.wikipedia.org/wiki/Miller-Rabin-Test
- https://de.wikipedia.org/wiki/Sieb_von_Atkin
- https://en.wikibooks.org/wiki/Cryptography/Generate_a_keypair_using_OpenSSL

### RSA
- https://de.wikipedia.org/wiki/RSA-Kryptosystem
- https://en.wikipedia.org/wiki/RSA_(cryptosystem)
- https://de.wikipedia.org/wiki/Bin%C3%A4re_Exponentiation
