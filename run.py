import subprocess
import os

def config():
  return subprocess.run(["cmake", "-B", "build"]).returncode == 0
  
def compile():
  return subprocess.run(["cmake", "--build", "build", "--config", "Debug"]).returncode == 0

def run():
  path = os.path.join("build", "tcp_echo_server")
  return subprocess.run([path, "-h"])

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
  
    

  