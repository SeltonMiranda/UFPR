for q in $(seq 1 8); do
  echo "Rodando questão q$q..."
  python autograder.py -q q$q
done
