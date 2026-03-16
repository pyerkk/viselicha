#include "hangman.h"
#include <iostream>

using namespace std;


void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void drawGallows(int errors) {
    setColor(YELLOW);
    cout << "\n  _______" << endl;
    cout << "  |     |" << endl;
    setColor(WHITE);
    cout << "  |     " << (errors > 0 ? "O" : "") << endl;
    cout << "  |    " << (errors > 2 ? "/" : " ") << (errors > 1 ? "|" : "") << (errors > 3 ? "\\" : "") << endl;
    cout << "  |    " << (errors > 4 ? "/" : "") << " " << (errors > 5 ? "\\" : "") << endl;
    cout << " _|_" << endl;
}

void printStatus(const string& guessed, int tries, int hints, const vector<char>& used) {
    setColor(CYAN);
    cout << "\nWord: ";
    setColor(WHITE);
    cout << guessed << endl;

    setColor(hints > 0 ? GREEN : RED);
    cout << "Tries left: " << tries << " | Hints: " << hints << endl;

    setColor(BLUE);
    cout << "Used: ";
    for (char c : used) cout << c << " ";
    setColor(WHITE);
    cout << "\n----------------------------" << endl;
}

vector<WordEntry> getLibrary() {
    return {
        // --- IT & COMPUTERS (40) ---
        {"algorithm", "IT: Logic steps"}, {"binary", "IT: 0s and 1s"}, {"compiler", "IT: Code translator"}, {"database", "IT: Data storage"},
        {"encryption", "IT: Hidden code"}, {"firewall", "IT: Net security"}, {"hardware", "IT: PC parts"}, {"interface", "IT: User bridge"},
        {"keyboard", "IT: Typing tool"}, {"mainframe", "IT: Giant PC"}, {"network", "IT: Connected PCs"}, {"protocol", "IT: Rules of net"},
        {"software", "IT: Programs"}, {"variable", "IT: Data container"}, {"website", "IT: Online page"}, {"browser", "IT: Web viewer"},
        {"desktop", "IT: Main screen"}, {"ethernet", "IT: Wired net"}, {"firmware", "IT: Built-in code"}, {"graphics", "IT: Visuals"},
        {"hyperlink", "IT: Web link"}, {"internet", "IT: World web"}, {"joystick", "IT: Game stick"}, {"kernel", "IT: OS heart"},
        {"laptop", "IT: Portable PC"}, {"monitor", "IT: PC screen"}, {"node", "IT: Net point"}, {"offline", "IT: No net"},
        {"password", "IT: Secret key"}, {"query", "IT: Data search"}, {"runtime", "IT: Executing time"}, {"server", "IT: Data giver"},
        {"terminal", "IT: Command line"}, {"upload", "IT: Sending file"}, {"virtual", "IT: Not physical"}, {"window", "IT: App frame"},
        {"xml", "IT: Data format"}, {"youtube", "IT: Video site"}, {"zip", "IT: Archive file"}, {"debugger", "IT: Bug finder"},

        // --- SPACE & SCIENCE (40) ---
        {"jupiter", "Space: Gas giant"}, {"galaxy", "Space: Star system"}, {"asteroid", "Space: Space rock"}, {"blackhole", "Space: Gravity trap"},
        {"eclipse", "Space: Sun shadow"}, {"nebula", "Space: Gas cloud"}, {"quantum", "Science: Tiny physics"}, {"molecule", "Science: Atom group"},
        {"telescope", "Science: Star tool"}, {"velocity", "Science: Speed"}, {"astronomy", "Science: Sky study"}, {"biology", "Science: Life study"},
        {"comet", "Space: Ice rock"}, {"dna", "Science: Genetic code"}, {"earth", "Space: Home planet"}, {"fossil", "Science: Ancient bone"},
        {"gravity", "Science: Pull force"}, {"helium", "Science: Light gas"}, {"isotope", "Science: Atom variant"}, {"kinetic", "Science: Motion"},
        {"laser", "Science: Light beam"}, {"mars", "Space: Red planet"}, {"neutron", "Science: Atom part"}, {"orbit", "Space: Path in sky"},
        {"photon", "Science: Light particle"}, {"quasar", "Space: Bright object"}, {"radar", "Science: Detection"}, {"saturn", "Space: Ring planet"},
        {"uranus", "Space: Cold planet"}, {"vacuum", "Space: Empty space"}, {"whitehole", "Space: Math object"}, {"xenon", "Science: Rare gas"},
        {"yellow", "Science: Color"}, {"zenith", "Space: Top point"}, {"atom", "Science: Basic unit"}, {"cell", "Science: Life unit"},
        {"energy", "Science: Power"}, {"fusion", "Science: Sun power"}, {"gravity", "Science: Earth pull"}, {"hydrogen", "Science: Element 1"},

        // --- NATURE & ANIMALS (40) ---
        {"elephant", "Nature: Gray giant"}, {"crocodile", "Nature: River toothy"}, {"avalanche", "Nature: Snow slide"}, {"tornado", "Nature: Wind swirl"},
        {"hurricane", "Nature: Big storm"}, {"kangaroo", "Nature: Jumper"}, {"platypus", "Nature: Weird mammal"}, {"scorpion", "Nature: Stinging bug"},
        {"volcano", "Nature: Fire mountain"}, {"waterfall", "Nature: Water drop"}, {"alligator", "Nature: Big reptile"}, {"butterfly", "Nature: Winged bug"},
        {"cheetah", "Nature: Fast cat"}, {"dolphin", "Nature: Sea mammal"}, {"eagle", "Nature: Big bird"}, {"forest", "Nature: Tree place"},
        {"giraffe", "Nature: Long neck"}, {"hyena", "Nature: Laughing dog"}, {"iguana", "Nature: Green lizard"}, {"jungle", "Nature: Rain forest"},
        {"koala", "Nature: Eucalyptus eater"}, {"leopard", "Nature: Spotted cat"}, {"mammoth", "Nature: Ice age giant"}, {"nightingale", "Nature: Song bird"},
        {"octopus", "Nature: 8 legs"}, {"panther", "Nature: Black cat"}, {"quokka", "Nature: Happy animal"}, {"raccoon", "Nature: Trash panda"},
        {"snake", "Nature: No legs"}, {"tiger", "Nature: Striped cat"}, {"undergrowth", "Nature: Bush floor"}, {"vulture", "Nature: Scavenger"},
        {"wolf", "Nature: Forest dog"}, {"xray", "Nature: Fish type"}, {"yak", "Nature: Shaggy cow"}, {"zebra", "Nature: Striped horse"},
        {"ant", "Nature: Tiny worker"}, {"bear", "Nature: Big furry"}, {"cactus", "Nature: Desert plant"}, {"desert", "Nature: Sand place"},

        // --- FOOD & DRINK (40) ---
        {"lasagna", "Food: Layer pasta"}, {"hamburger", "Food: Meat bun"}, {"croissant", "Food: French bread"}, {"guacamole", "Food: Green dip"},
        {"espresso", "Food: Strong coffee"}, {"omelette", "Food: Egg dish"}, {"spaghetti", "Food: Thin pasta"}, {"pancake", "Food: Round cake"},
        {"zucchini", "Food: Green veggie"}, {"broccoli", "Food: Mini tree"}, {"apple", "Food: Fruit"}, {"banana", "Food: Yellow fruit"},
        {"cherry", "Food: Red fruit"}, {"dumpling", "Food: Dough ball"}, {"eggplant", "Food: Purple veggie"}, {"falafel", "Food: Chickpea ball"},
        {"garlic", "Food: Smelly plant"}, {"honey", "Food: Bee sugar"}, {"icecream", "Food: Cold sweet"}, {"juice", "Food: Fruit drink"},
        {"kebab", "Food: Meat stick"}, {"lemon", "Food: Sour fruit"}, {"macaroni", "Food: Pasta tubes"}, {"noodle", "Food: Asian pasta"},
        {"orange", "Food: Orange fruit"}, {"pizza", "Food: Italian circle"}, {"quiche", "Food: Egg pie"}, {"ravioli", "Food: Pasta pillows"},
        {"sandwich", "Food: Bread layers"}, {"tomato", "Food: Red veggie"}, {"ugli", "Food: Weird fruit"}, {"vanilla", "Food: Sweet smell"},
        {"waffle", "Food: Grid cake"}, {"yogurt", "Food: Milk cream"}, {"apricot", "Food: Orange fruit"}, {"bacon", "Food: Fried meat"},
        {"cake", "Food: Birthday sweet"}, {"donut", "Food: Sweet ring"}, {"egg", "Food: Morning food"}, {"fish", "Food: Sea food"},

        // --- JOBS & HOBBIES (40) ---
        {"architect", "Job: Building designer"}, {"dentist", "Job: Tooth doctor"}, {"guitar", "Hobby: Music"}, {"jazz", "Hobby: Music style"},
        {"orchestra", "Hobby: Music group"}, {"engineer", "Job: Tech builder"}, {"journalist", "Job: News writer"}, {"sculptor", "Job: Stone artist"},
        {"librarian", "Job: Book keeper"}, {"astronomy", "Hobby: Sky watching"}, {"actor", "Job: Movie player"}, {"baker", "Job: Bread maker"},
        {"carpenter", "Job: Wood worker"}, {"driver", "Job: Car pilot"}, {"editor", "Job: Text fixer"}, {"farmer", "Job: Food grower"},
        {"gardener", "Job: Plant keeper"}, {"hunter", "Job: Forest worker"}, {"inventor", "Job: New thing maker"}, {"janitor", "Job: Cleaner"},
        {"knight", "Job: Sword fighter"}, {"lawyer", "Job: Law expert"}, {"musician", "Job: Music maker"}, {"nurse", "Job: Med helper"},
        {"officer", "Job: Law enforcer"}, {"pilot", "Job: Plane flyer"}, {"queen", "Job: Ruler"}, {"reporter", "Job: News giver"},
        {"soldier", "Job: Army worker"}, {"teacher", "Job: School worker"}, {"umpire", "Job: Game judge"}, {"vet", "Job: Pet doctor"},
        {"writer", "Job: Book maker"}, {"artist", "Job: Paint maker"}, {"boxer", "Job: Fighter"}, {"cook", "Job: Food maker"},
        {"dancer", "Job: Motion artist"}, {"hacker", "Job: PC explorer"}, {"magician", "Job: Trick maker"}, {"painter", "Job: Wall artist"},

        // --- OBJECTS & TOOLS (40) ---
        {"microscope", "Tool: Tiny things"}, {"telescope", "Tool: Star watching"}, {"hammer", "Tool: Nail hitter"}, {"scissors", "Tool: Cutting"},
        {"umbrella", "Object: Rain shield"}, {"backpack", "Object: Bag"}, {"camera", "Object: Photo tool"}, {"door", "Object: Room entry"},
        {"flashlight", "Object: Portable light"}, {"glasses", "Object: Eye helper"}, {"helmet", "Object: Head shield"}, {"iron", "Object: Cloth fixer"},
        {"jacket", "Object: Warm wear"}, {"knife", "Object: Sharp tool"}, {"lamp", "Object: Light source"}, {"mirror", "Object: Reflection"},
        {"notebook", "Object: Paper book"}, {"oven", "Object: Cooking box"}, {"pencil", "Object: Writing tool"}, {"quilt", "Object: Warm blanket"},
        {"radio", "Object: Music box"}, {"spoon", "Object: Eating tool"}, {"telephone", "Object: Call tool"}, {"vacuum", "Object: Dust sucker"},
        {"wallet", "Object: Money bag"}, {"watch", "Object: Time tool"}, {"anchor", "Object: Ship fixer"}, {"basket", "Object: Container"},
        {"clock", "Object: Time teller"}, {"drill", "Object: Hole maker"}, {"engine", "Object: Power maker"}, {"fork", "Object: Food tool"},
        {"guitar", "Object: Music tool"}, {"hook", "Object: Metal curve"}, {"instrument", "Object: Tool"}, {"key", "Object: Lock opener"},
        {"ladder", "Object: Climbing tool"}, {"needle", "Object: Sewing tool"}, {"pliers", "Object: Hand tool"}, {"saw", "Object: Wood cutter"},

        // --- PLACES & BUILDINGS (40) ---
        {"airport", "Place: Plane station"}, {"bakery", "Place: Bread shop"}, {"castle", "Place: King house"}, {"dungeon", "Place: Prison"},
        {"embassy", "Place: Gov office"}, {"factory", "Place: Work building"}, {"garage", "Place: Car house"}, {"hospital", "Place: Health place"},
        {"island", "Place: Sea land"}, {"jail", "Place: Crime house"}, {"kitchen", "Place: Cooking room"}, {"library", "Place: Book house"},
        {"museum", "Place: History house"}, {"nightclub", "Place: Party room"}, {"office", "Place: Work room"}, {"palace", "Place: Royal house"},
        {"quarry", "Place: Stone mine"}, {"restaurant", "Place: Food house"}, {"school", "Place: Learning room"}, {"theater", "Place: Stage house"},
        {"university", "Place: Study house"}, {"village", "Place: Small town"}, {"workshop", "Place: Making room"}, {"yard", "Place: House grass"},
        {"zoo", "Place: Animal house"}, {"attic", "Place: Top room"}, {"bank", "Place: Money house"}, {"church", "Place: Holy house"},
        {"dentist", "Place: Tooth house"}, {"farm", "Place: Animal home"}, {"gym", "Place: Sport room"}, {"hotel", "Place: Guest house"},
        {"iceberg", "Place: Cold island"}, {"lighthouse", "Place: Sea light"}, {"market", "Place: Shop place"}, {"nursery", "Place: Baby room"},
        {"park", "Place: Green place"}, {"river", "Place: Flowing water"}, {"stadium", "Place: Sport field"}, {"temple", "Place: Holy place"},

        // --- HARD & ABSTRACT (30) ---
        {"paradigm", "Hard: Model/Example"}, {"nostalgia", "Hard: Past longing"}, {"labyrinth", "Hard: Complex maze"}, {"synergy", "Hard: Combined work"},
        {"illusion", "Hard: Fake vision"}, {"dilemma", "Hard: Tough choice"}, {"hierarchy", "Hard: Rank system"}, {"oblivion", "Hard: Being forgotten"},
        {"resonance", "Hard: Echo/Vibration"}, {"utopia", "Hard: Perfect world"}, {"chaos", "Hard: No order"}, {"entropy", "Hard: Decay/Random"},
        {"facade", "Hard: Front view"}, {"garrulous", "Hard: Talkative"}, {"idiosyncrasy", "Hard: Unique habit"}, {"juxtapose", "Hard: Compare side"},
        {"kaleidoscope", "Hard: Changing patterns"}, {"melancholy", "Hard: Sad feeling"}, {"nefarious", "Hard: Wicked/Evil"}, {"omnipresent", "Hard: Everywhere"},
        {"quandary", "Hard: Confusion"}, {"reticent", "Hard: Quiet/Silent"}, {"surreptitious", "Hard: Secretive"}, {"transient", "Hard: Short-lived"},
        {"ubiquitous", "Hard: Common"}, {"vicarious", "Hard: Second-hand"}, {"whimsical", "Hard: Playful"}, {"zealous", "Hard: Passionate"},
        {"apathy", "Hard: No feeling"}, {"benevolent", "Hard: Kind heart"},

        // --- MIXED RANDOM (40) ---
        {"adventure", "Mix: Fun trip"}, {"balloon", "Mix: Air bag"}, {"calendar", "Mix: Date book"}, {"diamond", "Mix: Shiny stone"},
        {"energy", "Mix: Power"}, {"freedom", "Mix: No chains"}, {"growth", "Mix: Big change"}, {"history", "Mix: Past study"},
        {"identity", "Mix: Who you are"}, {"journey", "Mix: Travel"}, {"knowledge", "Mix: What you know"}, {"luck", "Mix: Good fate"},
        {"mystery", "Mix: Unknown thing"}, {"nature", "Mix: Outside world"}, {"opinion", "Mix: Your thought"}, {"peace", "Mix: No war"},
        {"quality", "Mix: Value"}, {"respect", "Mix: Good honor"}, {"silence", "Mix: No sound"}, {"treasure", "Mix: Hidden gold"},
        {"unity", "Mix: Together"}, {"victory", "Mix: Winning"}, {"wisdom", "Mix: Smart mind"}, {"xenon", "Mix: Gas"},
        {"yesterday", "Mix: Day before"}, {"zodiac", "Mix: Star signs"}, {"alpha", "Mix: First"}, {"beta", "Mix: Second"},
        {"gamma", "Mix: Third"}, {"delta", "Mix: Fourth"}, {"omega", "Mix: Last"}, {"silver", "Mix: Metal"},
        {"gold", "Mix: Metal"}, {"bronze", "Mix: Metal"}, {"stone", "Mix: Material"}, {"glass", "Mix: Material"},
        {"paper", "Mix: Material"}, {"plastic", "Mix: Material"}, {"cotton", "Mix: Material"}, {"wood", "Mix: Material"}
    };
}
