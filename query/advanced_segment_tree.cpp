
template <class T>
class advanced_segment_tree {
public:
  struct node_type;
  using root_type = node_type *;
  using value_type = typename T::value_type;
  using effector_type = typename T::effector_type;
  using size_type = size_t;
  using flag_type = bool;

  static inline const auto op1 = typename T::value_operation();
  static inline const auto op2 = typename T::merge_operation();

  struct node_type {
    root_type left, right;
    value_type value, sum;
    size_type size;
    flag_type reversed;
  };

  static uint64_t engine() {
    static uint64_t current = 7511168;
    current ^= (current << 9);
    current ^= (current >> 7);
    return current;
  }

private:
  root_type M_root;

  inline size_type size(root_type node) const {
    return node ? node -> size : 0;
  }
  inline value_type sum(root_type node) const {
    return node ? node -> sum : op1.identity;
  }
  inline root_type apply(root_type node) const {
    node -> size = size(node -> left) + size(node -> right) + 1;
    node -> sum = op1(op1(sum(node -> left), node -> value), sum(node -> right));
    return node;
  }
  inline void flush(root_type node) const {
    if (node -> reversed) {
      std::swap(node -> left, node -> right);
      if (node -> left) node -> left -> reversed ^= 1;
      if (node -> right) node -> right -> reversed ^= 1;
      node -> reversed = false;
    }
  }

  root_type M_merge_impl(root_type left, root_type right) const {
    if (!left || !right) return left ? left : right;
    if (engine() % (size(left) + size(right)) < size(left)) {
      flush(left);
      left -> right = M_merge_impl(left -> right, right);
      return apply(left);
    }
    else {
      flush(right);
      right -> left = M_merge_impl(left, right -> left);
      return apply(right);
    }
  }
  std::pair<root_type, root_type> M_split_impl(root_type node, size_type pos) const {
    if (!node) return { nullptr, nullptr };
    flush(node);
    if (pos <= size(node -> left)) {
      auto tmp = M_split_impl(node -> left, pos);
      node -> left = tmp.second;
      return { tmp.first, apply(node) };
    }
    else {
      auto tmp = M_split_impl(node -> right, pos - size(node -> left) - 1);
      node -> right = tmp.first;
      return { apply(node), tmp.second };
    }
  }

  root_type M_build_impl(const std::vector<value_type> &data, size_type l, size_type r) const {
    if (l >= r) return nullptr;
    size_type idx = engine() % (r - l) + l;
    return apply(new node_type{ M_build_impl(data, l, idx), M_build_impl(data, idx + 1, r), data[idx], data[idx], 1, false });
  }
  void M_clear_impl(root_type node) const {
    if (!node) return;
    M_clear_impl(node -> left);
    M_clear_impl(node -> right);
    delete node;
  }
  void M_dump_impl(root_type node, std::vector<value_type> &data) const {
    if (!node) return;
    flush(node);
    M_dump_impl(node -> left, data);
    data.push_back(node -> value);
    M_dump_impl(node -> right, data);
  }

  root_type M_insert_single_impl(root_type node, size_type idx, const value_type &val) const {
    auto tmp = M_split_impl(node, idx);
    return M_merge_impl(M_merge_impl(tmp.first, new node_type{ nullptr, nullptr, val, val, 1, false }), tmp.second);
  }
  root_type M_insert_range_impl(root_type node, size_type idx, const std::vector<value_type> &data) const {
    auto tmp = M_split_impl(node, idx);
    return M_merge_impl(M_merge_impl(tmp.first, M_build_impl(data, 0, data.size())), tmp.second);
  }
  root_type M_erase_single_impl(root_type node, size_type idx) const {
    auto left = M_split_impl(node, idx);
    auto right = M_split_impl(left.second, 1);
    delete right.first;
    return M_merge_impl(left.first, right.second);
  }
  root_type M_erase_range_impl(root_type node, size_type l, size_type r) const {
    auto left = M_split_impl(node, l);
    auto right = M_split_impl(left.second, r - l);
    M_clear_impl(right.first);
    return M_merge_impl(left.first, right.second);
  }

  void M_assign_impl(root_type node, size_type idx, const value_type &val) const {
    flush(node);
    if (idx == size(node -> left)) node -> value = val;
    else if (idx < size(node -> left)) M_assign_impl(node -> left, idx, val);
    else M_assign_impl(node -> right, idx - size(node -> left) - 1, val);
    apply(node);
  }
  void M_modify_impl(root_type node, size_type idx, const effector_type &val) const {
    flush(node);
    if (idx == size(node -> left)) node -> value = op2(node -> value, val);
    else if (idx < size(node -> left)) M_modify_impl(node -> left, idx, val);
    else M_modify_impl(node -> right, idx - size(node -> left) - 1, val);
    apply(node);
  }

  root_type M_copy_node_impl(root_type node) const {
    return new node_type(*node);
  }
  root_type M_copy_tree_impl(root_type node) const {
    if (!node) return nullptr;
    root_type res = M_copy_node_impl(node);
    res -> left = M_copy_tree_impl(node -> left);
    res -> right = M_copy_tree_impl(node -> right);
    return res;
  }

public:
  advanced_segment_tree(root_type root = nullptr): M_root(root) { }
  advanced_segment_tree(const std::vector<value_type> &data) { build(data); }
  ~advanced_segment_tree() { clear(); }

  advanced_segment_tree& operator = (const advanced_segment_tree &arr) {
    if (this != &arr) { clear(); M_root = arr.copy(); }
    return *this;
  }
  advanced_segment_tree& operator = (advanced_segment_tree &&arr) noexcept {
    if (this != &arr) { clear(); M_root = std::exchange(arr.extract(), nullptr); }
    return *this;
  }

  root_type extract() { 
    return M_root;
  }
  root_type copy() const {
    return M_copy_tree_impl(M_root);
  }

  void insert_at(size_type idx, const value_type &val) {
    M_root = M_insert_single_impl(M_root, idx, val);
  }
  void insert_range(size_type idx, const std::vector<value_type> &data) {
    M_root = M_insert_range_impl(M_root, idx, data);
  }
  void erase_at(size_type idx) {
    M_root = M_erase_single_impl(M_root, idx);
  }
  void erase_range(size_type l, size_type r) {
    M_root = M_erase_range_impl(M_root, l, r);
  }

  void push_front(const value_type &val) {
    M_root = M_merge_impl(new node_type{ nullptr, nullptr, val, val, 1, false }, M_root);
  }
  void push_back(const value_type &val) {
    M_root = M_merge_impl(M_root, new node_type{ nullptr, nullptr, val, val, 1, false });
  }
  void pop_front() {
    M_root = M_erase_single_impl(M_root, 0);
  }
  void pop_back() {
    M_root = M_erase_single_impl(M_root, size(M_root) - 1);
  }

  void assign(size_type idx, const value_type &val) {
    M_assign_impl(M_root, idx, val);
  }
  void modify(size_type idx, const effector_type &val) {
    M_modify_impl(M_root, idx, val);
  }
  void reverse(size_type l, size_type r) {
    auto left = M_split_impl(M_root, l);
    auto right = M_split_impl(left.second, r - l);
    if (right.first) right.first -> reversed ^= 1;
    M_root = M_merge_impl(left.first, M_merge_impl(right.first, right.second));
  }
  
  void build(const std::vector<value_type> &data) {
    M_root = M_build_impl(data, 0, data.size());
  }
  void clear() {
    M_clear_impl(M_root);
    M_root = nullptr;
  }
  flag_type empty() const {
    return size(M_root) == 0;
  }
  size_type size() const {
    return size(M_root);
  }

  value_type at(size_type idx) {
    root_type cur = M_root;
    size_type cnt = 0;
    while (true) {
      flush(cur);
      if (cnt + size(cur -> left) == idx) return cur -> value;
      else if (cnt + size(cur -> left) > idx) cur = cur -> left;
      else cnt += size(cur -> left) + 1, cur = cur -> right;
    }
  }
  value_type fold(size_type l, size_type r) {
    auto left = M_split_impl(M_root, l);
    auto right = M_split_impl(left.second, r - l);
    value_type res = sum(right.first);
    M_root = M_merge_impl(left.first, M_merge_impl(right.first, right.second));
    return res;
  }

  std::vector<value_type> dump(size_type l, size_type r) {
    auto left = M_split_impl(M_root, l);
    auto right = M_split_impl(left.second, r - l);
    std::vector<value_type> res;
    M_dump_impl(right.first, res);
    M_root = M_merge_impl(left.first, M_merge_impl(right.first, right.second));
    return res;
  }

};

