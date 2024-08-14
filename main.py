import json


def main() -> None:
    simple_dict = {
        "a": 1,
        "b": 3,
        "c": 5,
    }
    with open("simple_dict.json", "w") as file:
        json.dump(simple_dict, file)


if __name__ == "__main__":
    main()
