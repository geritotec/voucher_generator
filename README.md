# Docs PDF generator API

Requisitos (solo si vas a construir archivos ejecutables)

- Tener MacOS

1. Homebrew
2. OpenSSL
3. cURL
4. Boost
5. asio

```
brew install openssl curl boost asio
```

## Construir achivos

1. Editar CMakeLists para que incluya los directorios /include y asio.
2. navegar a pdf_generator/build y ejecutar ```% cmake ..``` y después ```% make```.