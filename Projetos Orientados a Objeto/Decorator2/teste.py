class Command:
    pass

class NullCommand(Command):
    pass

class NewCommand(Command):
    def __init__(self, id, nome):
        self.id = id
        self.nome = nome

class DeleteCommand(Command):
    def __init__(self, id):
        self.id = id

class GetCommand(Command):
    def __init__(self, id):
        self.id = id

class GetAllCommand(Command):
    pass

class ComandoReader:
    def __init__(self, reader):
        self.reader = reader

    def read(self):
        return self.reader.read()

    def readComando(self):
        line = self.read().strip()
        parts = line.split(' ', 1)
        comando = parts[0]
        argumentos = parts[1] if len(parts) > 1 else ''

        if comando == 'new':
            args = argumentos.split(' ', 1)
            if len(args) == 2:
                id = args[0]
                nome = args[1]
                return NewCommand(id, nome)
        
        elif comando == 'delete':
            if argumentos:
                return DeleteCommand(argumentos)
        
        elif comando == 'get':
            if argumentos:
                return GetCommand(argumentos)
        
        elif comando == 'all':
            return GetAllCommand()
        
        return NullCommand()


class StringReader:
    def __init__(self, stream):
        self.lines = stream.split('\n')
        self.index = 0

    def read(self):
        if self.index < len(self.lines):
            line = self.lines[self.index]
            self.index += 1
            return line
        else:
            return ''

# Testando o ComandoReader
stream = "new 1 nome\nget 1\ninvalid\nall"
reader = ComandoReader(StringReader(stream))

while True:
    command = reader.readComando()
    if isinstance(command, NullCommand):
        print(command)
        break
    elif isinstance(command, GetAllCommand):
        print(command)
    elif command:
        print(command)

# Saída esperada:
# <__main__.NewCommand object at 0x...>
# <__main__.GetCommand object at 0x...>
# <__main__.NullCommand object at 0x...>
# <__main__.GetAllCommand object at 0x...>
