import blockio
import threading
import time

def run_and_time(func, *args):
    start = time.time()
    try:
        func(*args)
    except Exception as e:
        print(f"{func.__name__} raised:", e)
    end = time.time()
    print(f"{func.__name__}({args}) took {end - start:.2f}s")

def test_threads(target, *args):
    threads = [threading.Thread(target=run_and_time, args=(target,) + args) for _ in range(3)]
    for t in threads: t.start()
    for t in threads: t.join()

if __name__ == "__main__":
    print("=== 测试 C1.1 测例1：阻塞 sleep 未释放 GIL ===")
    test_threads(blockio.blocking_io, 2)

    print("\n=== 测试 C1.1 测例2：阻塞 sleep 释放 GIL ===")
    test_threads(blockio.gil_safe_sleep, 2)

    print("\n=== 测试 C1.1 测例3：模拟慢 I/O 未释放 GIL ===")
    test_threads(blockio.simulate_io, 10)

    print("\n=== 测试 C1.1 测例4：计算密集任务 ===")
    test_threads(blockio.cpu_bound, 50000000)
