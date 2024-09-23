// pwGen.js

function getRandomInt(min, max) {
    return Math.floor(Math.random() * (max - min + 1)) + min;
}

function randVowel() {
    const vowels = 'aeiou';
    return vowels.charAt(getRandomInt(0, vowels.length - 1));
}

function randConsonant() {
    const consonants = 'bcdfghjklmnpqrstvwxyz';
    return consonants.charAt(getRandomInt(0, consonants.length - 1));
}

function isVowel(letter) {
    return 'aeiou'.includes(letter);
}

function getNextLetter(password) {
    // First letter is capital
    if (password.length === 0) {
        const isVowel = getRandomInt(1, 26) <= 5; // 5/26 chance of being a vowel
        const firstLetter = isVowel ? randVowel() : randConsonant();
        return firstLetter.toUpperCase();
    }

    // 1 in 15 chance of inserting a dash
    if (getRandomInt(1, 15) === 1 && password.charAt(password.length - 1) !== '-') {
        return '-';
    }

    const lastLetter = password.charAt(password.length - 1);
    let lastLetterVowel = isVowel(lastLetter);
    if (lastLetter === '-') lastLetterVowel = Boolean(getRandomInt(0, 1));

    // 1 in 10 chance of having two consonants or two vowels in a row
    if (getRandomInt(1, 10) === 1) {
        return lastLetterVowel ? randVowel() : randConsonant();
    }

    if (!lastLetterVowel) {
        return randVowel();
    }

    let nextLetter = randConsonant();

    // An 'h' may follow a consonant, but not another 'h'.
    if (nextLetter === 'h' && lastLetter !== '-' && !isVowel(lastLetter) && lastLetter !== 'h') {
        return 'h';
    } else {
        while (nextLetter === 'h') nextLetter = randConsonant();
    }

    // An 'l' may follow a consonant unless there's already a consonant followed by an 'l'
    if (nextLetter === 'l' && password.length >= 3 && lastLetter === 'l' && password.charAt(password.length - 2) !== '-' && !isVowel(password.charAt(password.length - 2))) {
        return 'l';
    } else {
        while (nextLetter === 'l') nextLetter = randConsonant();
    }

    // A 'c' may be followed by a 'k' if the 'c' follows a vowel (e.g. ack).
    if (nextLetter === 'k' && password.length >= 3 && lastLetter === 'c' && isVowel(password.charAt(password.length - 2))) {
        return 'k';
    } else {
        while (nextLetter === 'k') nextLetter = randConsonant();
    }

    return nextLetter;
}

function generatePassword(pwLength) {
    const specials = ['!', '@', '#', '$', '%', '^', '&'];
    let password = '';

    for (let i = 0; i < pwLength - 3; i++) {
        password += getNextLetter(password);
    }

    // Add symbol and number at end
    const symbolFirst = getRandomInt(0, 1) === 1;
    let twoDigits = String.fromCharCode(getRandomInt(48, 57)) + String.fromCharCode(getRandomInt(48, 57));

    if (symbolFirst) {
        password += specials[getRandomInt(0, specials.length - 1)];
        password += twoDigits;
    } else {
        password += twoDigits;
        password += specials[getRandomInt(0, specials.length - 1)];
    }

    return password;
}