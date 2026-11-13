import argparse
import socket

def main(message: str):

    s = socket.socket()

    # Gets hostname of
    s.connect((socket.gethostname(), 8000))

    s.sendall(message.encode())

    s.close()

if __name__ == "__main__":
    arg_parser = argparse.ArgumentParser()

    arg_parser.add_argument("-m", "--message", type=str)
    args = arg_parser.parse_args()

    main(args.message)