from collections import defaultdict


# Funcția pentru colectarea variabilelor de la utilizator
def get_variables():
    # Colectarea variabilelor
    variables = []
    num_vars = int(input("Enter number of variables: "))
    for i in range(num_vars):
        var = input(f"Var[{i}] in UPPERCASE: ")[0]
        variables.append(var)
    return variables


# Funcția pentru colectarea regulilor gramaticale de la utilizator
def get_rules(variables):
    rules = defaultdict(list)
    for var in variables:
        num_rules = int(input(f"Number of rules for {var}: "))
        for _ in range(num_rules):
            rule = input(f"{var} = ")
            rules[var].append(rule)
    return rules


# Funcția CYK care procesează substraturi
def cyk_algorithm(string, rules):

    def process_substring(substr, rules, cyk, length):
        result = set(
        )  # Set pentru a colecta variabilele care pot genera substratul
        for split_point in range(length -
                                 1):  # Împarte substratul în două părți
            first_part = cyk[
                substr[:split_point +
                       1]]  # Variabilele care pot genera prima parte
            second_part = cyk[
                substr[split_point +
                       1:]]  # Variabilele care pot genera a doua parte
            # Combină toate perechile de variabile și verifică dacă există o regulă care le generează concatenarea
            for combination in [
                    a + b for a in first_part for b in second_part
            ]:
                for key, rule_list in rules.items():
                    if combination in rule_list:
                        result.add(
                            key
                        )  # Adaugă variabila care poate genera substratul curent
        cyk[substr] = result
        # Actualizează dicționarul CYK cu rezultatul pentru substratul curent

    cyk = defaultdict(
        set
    )  # Dicționar CYK pentru a stoca variabilele care pot genera fiecare substrat
    n = len(string)

    for length in range(1, n + 1):
        for start in range(n - length + 1):
            substr = string[start:start + length]  # Substratul curent
            if length == 1:  # Inițializarea pentru substraturi de lungime 1
                for key, rule_list in rules.items():
                    if substr in rule_list:
                        cyk[substr].add(
                            key
                        )  # Adaugă variabila care poate genera substratul de lungime 1
            else:
                # Procesarea substraturilor de lungime mai mare
                process_substring(substr, rules, cyk, length)

    return cyk


# Funcția principală care colectează datele și rulează algoritmul CYK
def main():
    variables = get_variables()
    rules = get_rules(variables)
    string = input("Enter a string: ")
    cyk_result = cyk_algorithm(string, rules)

    # Verifică dacă simbolul de start 'S' poate genera cuvântul
    if 'S' in cyk_result[string]:
        print('Belongs')
    else:
        print('Not Belongs')


if __name__ == "__main__":
    main()
