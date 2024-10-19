import AsyncStorage from "@react-native-async-storage/async-storage"

const useStorage = () => {
//Search saved itens
    const getItem = async (key) => {
        try {
            const password = await AsyncStorage.getItem(key)
            return JSON.parse(password) || [];
            
        } catch (error) {
            console.log("Error in getItem:", error)
            return []
        }
    }
//Save item in storage
    const saveItem = async (key, value) => {
        try {
            let passwords = await getItem(key)
            passwords.push(value)

            await AsyncStorage.setItem(key, JSON.stringify(passwords))
            
        } catch (error) {
            console.log("Error in saveItem: ", error)
        }
    }
//Remove from storage
    const removeItem = async (key, item) => {
        try {
            let passwords = await getItem(key)
            let myPasswords = passwords.filter( (password) => {
                return (password !== item)
            })

            await AsyncStorage.setItem(key, JSON.stringify(myPasswords))
            return myPasswords
        } catch (error) {
            console.log("Error in removeItem: ", error)
        }
    }

    return{
        getItem,
        saveItem,
        removeItem
    }

}

export default useStorage;