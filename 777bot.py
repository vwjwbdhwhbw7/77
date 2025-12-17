#!/usr/bin/env python3
import sys
import subprocess
import time
import threading

if len(sys.argv) != 4:
    print("Usage: python3 script.py <target_url> <duration> <rate>")
    print("Example: python3 script.py target.com 30 70")
    sys.exit(1)

target = sys.argv[1]
duration = int(sys.argv[2])
rate = int(sys.argv[3])

def send_wget():
    try:
        subprocess.Popen(['wget', '-q', '-O', '/dev/null', 'http://' + target],
                        stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
    except:
        pass

print(f"Sending {rate} wget requests/second to {target} for {duration} seconds...")
count = 0
end_time = time.time() + duration

while time.time() < end_time:
    threads = []
    for i in range(rate):
        t = threading.Thread(target=send_wget)
        threads.append(t)
        t.start()
        count += 1
    time.sleep(1)

print(f"Sent {count} total wget requests")