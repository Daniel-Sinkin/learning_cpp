import json


def main() -> None:
    simple_dict = {
        "a": 1,
        "b": 3,
        "c": [2, 4, "a", "b"],
    }
    with open("simple_dict.json", "w") as file:
        json.dump(simple_dict, file)


if __name__ == "__main__":
    main()
