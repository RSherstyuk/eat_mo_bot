class TreeNode:
    def __init__(self, val) -> None:
        self.val = val
        self.left = None
        self.right = None


class BTree:
    def __init__(self) -> None:
        self.root = None

    def inseart_recursive(self, root: TreeNode | None, val):
        if self.root is None:
            return TreeNode(val)
        if val < root.val:
            self.inseart_recursive(root.left, val)
        else:
            self.inseart_recursive(root.right, val)

    # Строим дерево по уровням (Level-order), чтобы
    # массив [1, 2, 2, 3, 4, 4, 3] образовал симметричную структуру
    def add_level_order(self, arr):
        if not arr:
            return
        self.root = TreeNode(arr[0])
        queue = [self.root]
        i = 1

        while i < len(arr):
            current = queue.pop(0)

            if i < len(arr) and arr[i] is not None:
                current.left = TreeNode(arr[i])
                queue.append(current.left)
            i += 1

            if i < len(arr) and arr[i] is not None:
                current.right = TreeNode(arr[i])
                queue.append(current.right)
            i += 1

    def insert(self, num):
        if self.root is None:
            self.root = TreeNode(num)  # Или как называется ваш класс узла
        else:
            self.inseart_recursive(self.root, num)

    def print_tree(self):
        self._print_node(self.root)

    def _print_node(self, node):
        if not node:
            return

        print(node.val)
        print("-----")

        self._print_node(node.left)
        self._print_node(node.right)


def isSymmetric(root: TreeNode | None) -> bool:
    if not root:
        return True

    # Кладем в стек левого и правого ребенка корня
    stack = [root.left, root.right]

    step = 1
    while stack:
        print(f"\n--- Шаг {step} ---")
        print(f"Стек до pop: {[n.val if n else None for n in stack]}")

        # Достаем пару узлов для сравнения
        # В Python pop() забирает элемент с конца списка
        right = stack.pop()
        left = stack.pop()

        print(
            f"Достали для сравнения: left={left.val if left else None}, right={right.val if right else None}"
        )

        if not left and not right:
            print("Оба узла пусты (None). Идем дальше.")
            step += 1
            continue

        if not left or not right or left.val != right.val:
            print("Нарушение симметрии!")
            return False

        # Кладем детей в стек в ЗЕРКАЛЬНОМ порядке:
        # 1. Крайние узлы с крайними
        stack.append(left.left)
        stack.append(right.right)

        # 2. Внутренние узлы с внутренними
        stack.append(left.right)
        stack.append(right.left)

        print(f"Стек после добавления детей: {[n.val if n else None for n in stack]}")
        step += 1

    return True


def main():
    bt = BTree()
    arr = [1, 2, 2, 3, 4, 4, 3]

    for num in arr:
        bt.insert(num)

    bt.print_tree()

    result = isSymmetric(bt.root)
    print(f"\nИтог: дерево симметрично? {result}")


if __name__ == "__main__":
    main()
