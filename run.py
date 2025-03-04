import subprocess
import os

def config():
  return subprocess.run(["cmake", "-B", "build", "-DTCP_ECHO_SERVER_BUILD_TEST=ON"]).returncode == 0
  
def compile():
  return subprocess.run(["cmake", "--build", "build", "--config", "Debug"]).returncode == 0

def run():
  # todo
  path = os.path.join("build", "tcp_echo_server")
  return subprocess.run([path, "-p", "7777", "-m", "2", "-b", "1024", "-t", "5000"])

def main():
  print("Configuring project:")
  if not config():
    print("Failed configuration")
    return
  print("Succesfully configuration")
  if not compile():
    print("Failed compile")
    return
  print("Succesfully compile")
  if not run():
    print("Failed run")
    return

if __name__ == "__main__":
  main()