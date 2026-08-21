import sys
import os

class FuzzerLogParser:
    def __init__(self, log_path):
        self.log_path = log_path
        self.summary = {
            'total_ops': 0,
            'failures': 0,
            'failed_seeds': []
        }

    def parse(self):
        if not os.path.exists(self.log_path):
            print(f"[!] Log file not found at: {self.log_path}")
            print("[!] Run the fuzzers first and pipe the output to a log file.")
            return False
            
        try:
            with open(self.log_path, 'r', encoding='utf-8') as f:
                for line in f:
                    self.summary['total_ops'] += 1
                    if 'FAIL' in line.upper() or 'ERROR' in line.upper() or 'SEGV' in line.upper():
                        self.summary['failures'] += 1
                        parts = line.split()
                        if 'seed' in [p.lower() for p in parts]:
                            # Attempt to extract seed value if present in the format 'seed 12345'
                            for i, part in enumerate(parts):
                                if part.lower() == 'seed' and i + 1 < len(parts):
                                    self.summary['failed_seeds'].append(parts[i+1])
                                    break
            return True
        except Exception as e:
            print(f"[!] Error reading log file: {e}")
            return False

    def report(self):
        print("\n" + "="*50)
        print(" 🚀 FUZZER LOG CRASH SUMMARY ".center(50, "="))
        print("="*50)
        print(f"  Total Log Lines Scanned : {self.summary['total_ops']}")
        print(f"  Detected Failures       : {self.summary['failures']}")
        
        if self.summary['failures'] > 0:
            print("\n  [!] INVESTIGATION REQUIRED [!]")
            if self.summary['failed_seeds']:
                seeds_str = ', '.join(set(self.summary['failed_seeds']))
                print(f"  Triggering Seeds: {seeds_str}")
        else:
            print("\n  [✓] ALL CLEAR. No failures detected in log.")
        print("="*50 + "\n")

if __name__ == '__main__':
    # Default to fuzzer_output.log in the build directory if no argument is provided
    target_log = sys.argv[1] if len(sys.argv) > 1 else 'build/fuzzer_output.log'
    parser = FuzzerLogParser(target_log)
    if parser.parse():
        parser.report()
