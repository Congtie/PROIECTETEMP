import sys


class DFA:

  def __init__(self, num_states, states, num_letters, letters, initial_state,
               num_final_states, final_states, transitions):
    self.num_states = num_states
    self.states = states
    self.num_letters = num_letters
    self.letters = letters
    self.initial_state = initial_state
    self.num_final_states = num_final_states
    self.final_states = final_states
    self.transitions = {state: {} for state in states}
    for (src, letter, dest) in transitions:
      self.transitions[src][letter] = dest

  @staticmethod
  def read_dfa(file_path):
    with open(file_path, 'r') as file:
      num_states = int(file.readline().strip())
      states = file.readline().strip().split()
      num_letters = int(file.readline().strip())
      letters = file.readline().strip().split()
      initial_state = file.readline().strip()
      num_final_states = int(file.readline().strip())
      final_states = file.readline().strip().split()
      num_transitions = int(file.readline().strip())
      transitions = []
      for _ in range(num_transitions):
        src, letter, dest = file.readline().strip().split()
        transitions.append((src, letter, dest))

    return DFA(num_states, states, num_letters, letters, initial_state,
               num_final_states, final_states, transitions)


def intersect_dfa(dfa1, dfa2):
  new_states = {f"{s1}-{s2}" for s1 in dfa1.states for s2 in dfa2.states}
  new_initial_state = f"{dfa1.initial_state}-{dfa2.initial_state}"
  new_final_states = {
      f"{s1}-{s2}"
      for s1 in dfa1.final_states
      for s2 in dfa2.final_states
  }
  new_transitions = []
  for s1 in dfa1.states:
    for s2 in dfa2.states:
      for letter in dfa1.letters:
        if letter in dfa1.transitions[s1] and letter in dfa2.transitions[s2]:
          new_src = f"{s1}-{s2}"
          new_dest = f"{dfa1.transitions[s1][letter]}-{dfa2.transitions[s2][letter]}"
          new_transitions.append((new_src, letter, new_dest))

  return DFA(len(new_states), list(new_states), dfa1.num_letters,
             dfa1.letters, new_initial_state, len(new_final_states),
             list(new_final_states), new_transitions)


#
if __name__ == "__main__":
  print("Introduceti calea catre fisierul pentru DFA1:")
  file_path1 = input().strip()
  dfa1 = DFA.read_dfa(file_path1)

  print("Introduceti calea catre fisierul pentru DFA2:")
  file_path2 = input().strip()
  dfa2 = DFA.read_dfa(file_path2)

  intersection_dfa = intersect_dfa(dfa1, dfa2)
  print("DFA-ul are urmatoarele proprietati:")
  print(f"Stari: {intersection_dfa.states}")
  print(f"Starea initiala: {intersection_dfa.initial_state}")
  print(f"Stari finale: {intersection_dfa.final_states}")
  print(f"Tranzitii: {intersection_dfa.transitions}")
