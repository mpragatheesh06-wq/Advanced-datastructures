class RetroactiveStack:
    def __init__(self):
        # List of operations tuple: (time, operation_type, value)
        self.operations = []
        
    def add_operation(self, t, op, val=None):
        if op not in ('push', 'pop'):
            raise ValueError("Operation must be 'push' or 'pop'")
        self.operations.append((t, op, val))
        self.operations.sort(key=lambda x: x[0])
        
    def query(self, t):
        # Replay operations up to time t
        stack = []
        for op_time, op, val in self.operations:
            if op_time > t:
                break
            if op == 'push':
                stack.append(val)
            elif op == 'pop':
                if stack:
                    stack.pop()
        return stack
        
    def top(self, t):
        stack = self.query(t)
        if stack:
            return stack[-1]
        return None

if __name__ == "__main__":
    rs = RetroactiveStack()
    rs.add_operation(1, 'push', 10)
    rs.add_operation(3, 'push', 20)
    rs.add_operation(5, 'pop')
    rs.add_operation(2, 'push', 15)  # retroactively insert push
    
    print("Stack at time 0:", rs.query(0))
    print("Stack at time 1:", rs.query(1))
    print("Stack at time 2:", rs.query(2))
    print("Stack at time 3:", rs.query(3))
    print("Stack at time 4:", rs.query(4))
    print("Stack at time 6:", rs.query(6))
