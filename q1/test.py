__author__ = 'chanita'
run_result = open("run_result.txt","rU")
missing = run_result.read().splitlines()

correct_answer = ("0001",
"0010",
"0011",
"0091",
"0097",
"0100",
"0242",
"1489",
"3567",
"3568",
"3574",
"3721",
"4259",
"4425",
"7727",
"8700",
"8889",
"9102",
)

missing_count = len(correct_answer)
your_correct_answer_count = 0
your_wrong_answer_count = 0

test_passed = False

for m in correct_answer:
    if m in missing:
        print "+ %s is missing." % m
        your_correct_answer_count += 1
    else:
        print "- %s is NOT missing." % m
        your_wrong_answer_count += 1
if your_correct_answer_count == missing_count == len(missing): test_passed =True

print "correct: %s " % your_correct_answer_count
print "wrong: %s " % your_wrong_answer_count
print "your answer of missing count: %s" % len(missing)
print "correct missing count: %s " % missing_count
print
print "PASS" if test_passed else "FAIL"