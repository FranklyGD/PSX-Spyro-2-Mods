class Syms:

    def __init__(self) -> None:
        self.symbols = dict()

    def add_symbols(self, path: str) -> None:
        with open(path, "r") as file:
            for line in file:
                line = [l.strip() for l in line.split("=") if l.strip() != '']
                if len(line) == 0:
                    continue
                if len(line) == 2:
                    symbol = line[0]
                    addr = int(line[1][:-1], 0)
                    self.symbols[addr] = symbol
                else:
                    print("WARNING! Wrong syntax at line:")
                    print(line)

    def get_symbol(self, addr: int) -> str:
        if addr in self.symbols:
            return self.symbols[addr]
        return None
