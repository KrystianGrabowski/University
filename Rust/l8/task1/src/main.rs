fn main() {
    println!("{:?}", dna_strand("AAAA"));
}

fn dna_strand(dna: &str) -> String {
    dna.chars().map(|x| match x {
        'A' => 'T',
        'T' => 'A',
        'G' => 'C',
        'C' => 'G',
        _ => ' '
    }).collect()
}

#[cfg(test)]
mod tests {
    use super::dna_strand;

    #[test]
    fn dna_strand_test_1() {
        assert_eq!(dna_strand("AAAA"),"TTTT");
    }
    #[test]
    fn dna_strand_test_2() {
        assert_eq!(dna_strand("ATTGC"),"TAACG");
    }
    #[test]
    fn dna_strand_test_3() {
        assert_eq!(dna_strand("GTAT"),"CATA");
    }
    #[test]
    fn dna_strand_test_4() {
        assert_eq!(dna_strand("CCCC"),"GGGG");
    }
    #[test]
    fn dna_strand_test_5() {
        assert_eq!(dna_strand("GGGG"),"CCCC");
    }
    #[test]
    fn dna_strand_test_6() {
        assert_eq!(dna_strand("ACACAC"),"TGTGTG");
    }
    #[test]
    fn dna_strand_test_7() {
        assert_eq!(dna_strand("TGTGTG"),"ACACAC");
    }
    #[test]
    fn dna_strand_test_8() {
        assert_eq!(dna_strand("ACGT"),"TGCA");
    }
    #[test]
    fn dna_strand_test_9() {
        assert_eq!(dna_strand("TTTAAAGGG"),"AAATTTCCC");
    }
    #[test]
    fn dna_strand_test_10() {
        assert_eq!(dna_strand("G"),"C");
    }
}