import ctypes

class Task(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_int),
        ("priority", ctypes.c_int),
        ("state", ctypes.c_int),
        ("function", ctypes.c_void_p),
        ("arg", ctypes.c_void_p),
    ]

print("Size of Task struct:", ctypes.sizeof(Task))

# Load the shared library
lib = ctypes.CDLL('../build/libscheduler.so')

# Define function signatures
lib.queue_init.argtypes = [ctypes.c_int]
lib.queue_init.restype = ctypes.c_void_p

# Helper function to create a task struct
def create_task(id, priority):
    return Task(id, priority, 0, None, None)  # Default READY state is 0


lib.queue_add.argtypes = [ctypes.c_void_p, ctypes.POINTER(create_task(0, 0).__class__)]
lib.queue_add.restype = None

lib.queue_remove.argtypes = [ctypes.c_void_p, ctypes.c_int]
lib.queue_remove.restype = None

lib.queue_list.argtypes = [ctypes.c_void_p]
lib.queue_list.restype = None

# Test Functions
def test_queue_functions():
    print("=== Testing Queue Functions ===")

    # Initialize the queue
    max_tasks = 10
    queue = lib.queue_init(max_tasks)
    if not queue:
        print("Failed to initialize the queue.")
        return
    print(f"Queue initialized with capacity {max_tasks}.")

    # Add tasks to the queue
    print("Adding tasks...")
    tasks = []  # Keeps references to Task objects
    for i in range(3):
        task = create_task(i + 1, (i + 1) * 5)
        tasks.append(task)  # Keep a reference to the task
        print(f"About to add, Task ID: {task.id}, Priority: {task.priority}")
        lib.queue_add(queue, ctypes.pointer(task))
        print(f"Added Task ID: {task.id}, Priority: {task.priority}")


    # List tasks in the queue
    print("Listing tasks in the queue:")
    lib.queue_list(queue)

    # Remove a task from the queue
    print("Removing Task ID: 1...")
    lib.queue_remove(queue, 1)
    print("Task removed.")

    # List tasks again
    print("Listing tasks after removal:")
    lib.queue_list(queue)

    print("=== Testing Completed ===")


if __name__ == "__main__":
    test_queue_functions()