
//user Class to save all the userData.

class User {
constructor(userNameX, displayNameX, passwordX, imgX) {
        this.userName = userNameX;
        this.displayName = displayNameX;
        this.password = passwordX;
        this.img = imgX;
        this.userChats = new Map();
    }
    getUserName () {
        return this.username;
    }
}

export default User